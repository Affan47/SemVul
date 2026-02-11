store_key_options(THD *thd, String *packet, TABLE *table,
                              KEY *key_info)
{
  bool limited_mysql_mode= (thd->variables.sql_mode &
                            (MODE_NO_FIELD_OPTIONS | MODE_MYSQL323 |
                             MODE_MYSQL40)) != 0;
  bool foreign_db_mode=  (thd->variables.sql_mode & (MODE_POSTGRESQL |
                                                     MODE_ORACLE |
                                                     MODE_MSSQL |
                                                     MODE_DB2 |
                                                     MODE_MAXDB |
                                                     MODE_ANSI)) != 0;
  char *end, buff[32];

  if (!(thd->variables.sql_mode & MODE_NO_KEY_OPTIONS) &&
      !limited_mysql_mode && !foreign_db_mode)
  {

    if (key_info->algorithm == HA_KEY_ALG_BTREE)
      packet->append(STRING_WITH_LEN(" USING BTREE"));

    if (key_info->algorithm == HA_KEY_ALG_HASH)
      packet->append(STRING_WITH_LEN(" USING HASH"));


    if ((key_info->algorithm == HA_KEY_ALG_RTREE) &&
        !(key_info->flags & HA_SPATIAL))
      packet->append(STRING_WITH_LEN(" USING RTREE"));

    if ((key_info->flags & HA_USES_BLOCK_SIZE) &&
        table->s->key_block_size != key_info->block_size)
    {
      packet->append(STRING_WITH_LEN(" KEY_BLOCK_SIZE="));
      end= longlong10_to_str(key_info->block_size, buff, 10);
      packet->append(buff, (uint) (end - buff));
    }
    DBUG_ASSERT(test(key_info->flags & HA_USES_COMMENT) ==
               (key_info->comment.length > 0));
    if (key_info->flags & HA_USES_COMMENT)
    {
      packet->append(STRING_WITH_LEN(" COMMENT "));
      append_unescaped(packet, key_info->comment.str,
                       key_info->comment.length);
    }
  }
}
