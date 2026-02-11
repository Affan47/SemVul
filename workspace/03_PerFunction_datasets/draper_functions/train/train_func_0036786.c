db_open(s, lrgintflg)
char *s;
char **lrgintflg;
   {
   char *msg_buf;
   char *id;
   int i, n;
   register int c;
   static int first_time = 1;

   if (first_time) {
      first_time = 0;
      init_sbuf(&db_sbuf);
      }
   dbname = s;
   dbline = 0;
   *lrgintflg = NULL;
   db = fopen(dbname, "rb");
   if (db == NULL)
      return 0;
   ++dbline;


   s = db_string();
   if (strcmp(s, DVersion) != 0) {
      msg_buf = alloc(35 + strlen(s) + strlen(progname) + strlen(DVersion));
      sprintf(msg_buf, "found version %s, %s requires version %s",
           s, progname, DVersion);
      db_err1(1, msg_buf);
      }

   *lrgintflg = db_string();


   type_map = alloc(num_typs * sizeof(int));
   db_chstr("", "types");
   c = getc(db);
   SkipWhSp(c)
   while (c == 'T') {
      c = getc(db);
      if (!isdigit(c))
         db_err1(1, "expected type code");
      GetInt(n, c)
      if (n >= num_typs)
         db_err1(1, "data base inconsistant with program, rebuild data base");
      SkipWhSp(c)
      if (c != ':')
         db_err1(1, "expected ':'");
      id = db_string();
      for (i = 0; strcmp(id, icontypes[i].id) != 0; ++i)
         if (i >= num_typs)
            db_err2(1, "unknown type:", id);
      type_map[n] = i;
      c = getc(db);
      SkipWhSp(c)
      }
   db_chstr("", "endsect");

   compnt_map = alloc(num_cmpnts * sizeof(int));
   db_chstr("", "components");
   c = getc(db);
   SkipWhSp(c)
   while (c == 'C') {
      c = getc(db);
      if (!isdigit(c))
         db_err1(1, "expected type component code");
      GetInt(n, c)
      if (n >= num_cmpnts)
         db_err1(1, "data base inconsistant with program, rebuild data base");
      SkipWhSp(c)
      if (c != ':')
         db_err1(1, "expected ':'");
      id = db_string();
      for (i = 0; strcmp(id, typecompnt[i].id) != 0; ++i)
         if (i >= num_cmpnts)
            db_err2(1, "unknown type component:", id);
      compnt_map[n] = i;
      c = getc(db);
      SkipWhSp(c)
      }
   db_chstr("", "endsect");

   return 1;
   }
