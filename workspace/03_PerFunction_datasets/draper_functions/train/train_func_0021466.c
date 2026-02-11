get_restore_client_name(UAContext *ua, RESTORE_CTX &rx)
{

   bstrncpy(rx.RestoreClientName, rx.ClientName, sizeof(rx.RestoreClientName));


   int i = find_arg_with_value(ua, NT_("restoreclient"));
   if (i >= 0) {
      if (!is_name_valid(ua->argv[i], &ua->errmsg)) {
         ua->error_msg("%s argument: %s", ua->argk[i], ua->errmsg);
         return 0;
      }
      bstrncpy(rx.RestoreClientName, ua->argv[i], sizeof(rx.RestoreClientName));
      return 1;
   }
   return 1;
}
