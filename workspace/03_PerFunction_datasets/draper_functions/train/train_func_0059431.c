CreateNewUser(char *Callsign)
{
   UserInfo *pUser = malloc(sizeof(UserInfo));

   if(pUser != NULL) {
      memset(pUser,0,sizeof(UserInfo));
      pUser->Callsign = strdup(Callsign);
      pUser->NodeID = Id++;
   }
   return pUser;
}
