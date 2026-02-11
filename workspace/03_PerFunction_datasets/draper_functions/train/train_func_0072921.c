RelabelOnConnect(){
    if (sn_GetNetState()==nCLIENT){
        tArray<tJUST_CONTROLLED_PTR<nNetObject> > sn_netObjects_old;


        int i;
        for(i=sn_netObjects.Len()-1;i>=0;i--){
            sn_netObjects_old[i]=sn_netObjects(i);
            sn_netObjects(i)=NULL;
            sn_netObjectsOwner[i]=0;
        }


        for(i=sn_netObjects_old.Len()-1;i>=0;i--){
            nNetObject *no = sn_netObjects_old(i);
            if (no){
                unsigned short id=next_free();

#ifdef DEBUG
                sn_BreakOnObjectID( id );
#endif

#ifdef DEBUG

#endif
                no->id=id;
                no->owner=::sn_myNetID;
                sn_netObjectsOwner[id]=::sn_myNetID;
                for(int j=MAXCLIENTS;j>=0;j--){
                    no->knowsAbout[j].Reset();
                    no->DoBroadcastExistence();
                }

                if (sn_netObjects[id])
                    st_Breakpoint();

                sn_netObjects[id]=no;
                sn_netObjects_old(i)=NULL;
            }
        }
    }
    (new nMessage(ready))->Send(0);
    is_ready_to_get_objects[0]=true;
}
