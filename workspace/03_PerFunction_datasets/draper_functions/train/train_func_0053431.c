createComposeContext(){
  if(!composeContext){
    composeContext=new FXComposeContext(getApp(),this,0);
    composeContext->create();
    }
  }
