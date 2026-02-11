check_auth_users_cache(char *user, const char *pw, request_rec *r, long now)
{


  UserCacheEntry *cache_entry = NULL;

  if (!auth_users) {
      ap_log_error(APLOG_MARK, APLOG_CRIT, 0 , NULL,
          "[%d] auth_users doesn't exist", getpid());
      return DECLINED;
  }

  cache_entry = (UserCacheEntry*)HashTableFind(auth_users, user);

  if (cache_entry) {
      ap_log_error(APLOG_MARK, APLOG_DEBUG, 0 , NULL,
                   "[%d] Found cache entry for user [%s][%s] pw is %s, cached is %s, now is %ld, cached is %ld",
                   getpid(), user, cache_entry->userDN, pw, cache_entry->userPW, now, cache_entry->createTime);
  } else {
      ap_log_error(APLOG_MARK, APLOG_DEBUG, 0 , NULL,
                   "[%d] cache entry not found for user [%s]",
                   getpid(), user);
  }


  if (!cache_entry || STRCMP(cache_entry->userPW, pw) ||
      ((now - cache_entry->createTime) > cacheLifetime)) {
      ap_log_error(APLOG_MARK, APLOG_DEBUG, 0 , NULL,
                   "[%d] user [%s] not cached - reason %s",
                   getpid(), user,
                   !cache_entry ? "user not in cache" :
                   (STRCMP(cache_entry->userPW, pw) ? "password changed" : "cache entry expired"));
      return DECLINED;
  }

  apr_table_set(r->notes, RQ_NOTES_USERDN, cache_entry->userDN);
  apr_table_set(r->notes, RQ_NOTES_USERPW, pw);


  return OK;
}
