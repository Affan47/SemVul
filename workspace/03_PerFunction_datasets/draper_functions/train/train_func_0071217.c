ConnectToDataSource()


{

  fileSystemInteractionManager.SetEnableRejectionOfIncompleteWlFiles( enableRejectionOfIncompleteWlFiles );


  OFCondition cond = fileSystemInteractionManager.ConnectToFileSystem( dfPath );


  return( cond );
}
