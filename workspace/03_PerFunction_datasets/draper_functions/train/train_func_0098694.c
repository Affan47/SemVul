ooH323EpSetGkClientCallbacks(OOGKCLIENTCALLBACKS gkClientCallbacks)
{

   if(gH323ep.gkClient)
   {
      return ooGkClientSetCallbacks(gH323ep.gkClient, gkClientCallbacks);
   }
   else{
      OOTRACEERR1("Error:Gk Client hasn't been initialized yet\n");
      return OO_FAILED;
   }

}
