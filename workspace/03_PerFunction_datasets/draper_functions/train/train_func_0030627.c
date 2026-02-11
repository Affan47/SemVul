_ecore_con_url_perform(Ecore_Con_Url *url_con)
{
   CURLMcode ret;

   ret = curl_multi_add_handle(_curlm, url_con->curl_easy);
   if (ret != CURLM_OK)
     {
        ERR("curl_multi_add_handle() failed: %s", curl_multi_strerror(ret));
        return EINA_FALSE;
     }

   url_con->multi = EINA_TRUE;
   _url_con_list = eina_list_append(_url_con_list, url_con);
   ecore_timer_thaw(_curl_timer);

   return EINA_TRUE;
}
