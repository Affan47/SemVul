BuildProcessTree()
{
  for (size_t j = 0; j < targets.size(); ++j)
  {
    VirtualPidTable& virtualPidTable = targets[j].getVirtualPidTable();
    originalPidTable.insertFromVirtualPidTable ( virtualPidTable );
    if( virtualPidTable.isRootOfProcessTree() == true ){

      RootTarget rt;
      rt.t = &targets[j];
      rt.indep = true;
      roots.push_back(rt);
      targets[j]._used = true;
    }else if( !targets[j]._used ){


      JTRACE("Process is not root of process tree: try to find if it has parent");
      bool is_root = true;
      for (size_t i = 0; i < targets.size(); i++) {
        VirtualPidTable & virtualPidTable = targets[i].getVirtualPidTable();
        VirtualPidTable::iterator it;

        for (it = virtualPidTable.begin(); (i != j) && (it != virtualPidTable.end()) ; it++) {
          UniquePid& childUniquePid = it->second;
          JTRACE("Check child")(childUniquePid)(" parent ")(targets[i].upid())("checked ")(targets[j].upid());
          if (childUniquePid == targets[j].upid()){
            is_root = false;
            break;
          }
        }
      }
      JTRACE("Root detection:")(is_root)(targets[j].upid());
      if( is_root ){
        RootTarget rt;
        rt.t = &targets[j];
        rt.indep = true;
        roots.push_back(rt);
        targets[j]._used = true;
      }
    }


    VirtualPidTable::iterator it;
    for(it = virtualPidTable.begin(); it != virtualPidTable.end(); it++ ){

      bool found = false;
      pid_t childOriginalPid = it->first;
      UniquePid& childUniquePid = it->second;

      for ( size_t i = 0; i < targets.size(); i++ )
      {
        if ( childUniquePid == targets[i].upid() )
        {
          found = 1;
          JTRACE ( "Add child to current target" ) ( targets[j].upid() ) ( childUniquePid );
          targets[i]._used = true;
          targets[j].addChild(&targets[i]);
        }
      }
      if ( !found ){
        JTRACE("Child not found")(childOriginalPid);
        virtualPidTable.erase( childOriginalPid );
      }
    }
  }
}
