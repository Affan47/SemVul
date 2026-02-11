cp_initialize(cut_pool *cp, int master_tid)
{
#ifndef COMPILE_IN_CP
   int bytes;
#if defined(COMPILE_IN_TM) && defined(COMPILE_IN_LP)
   int s_bufid, r_bufid;
#endif
#endif
#if !defined(COMPILE_IN_TM) || !defined(COMPILE_IN_LP)
   int s_bufid, r_bufid;
#endif


#ifdef COMPILE_IN_CP

   cp->master = master_tid;

#else


   setvbuf(stdout, (char *)NULL, _IOLBF, 0);

   register_process();

   r_bufid = receive_msg(ANYONE, MASTER_TID_INFO);
   bufinfo(r_bufid, &bytes, &cp->msgtag, &cp->tree_manager);
   receive_int_array(&cp->master, 1);
   freebuf(r_bufid);

#endif

#if !defined(COMPILE_IN_TM) || !defined(COMPILE_IN_CP)

   s_bufid = init_send(DataInPlace);
   send_msg(cp->master, REQUEST_FOR_CP_DATA);
   freebuf(s_bufid);

   receive_cp_data_u(cp);

#endif

   if (cp->par.warm_start == READ_CP_LIST){
      read_cp_cut_list(cp, cp->par.warm_start_file_name);
   }else if (cp->par.warm_start == READ_TM_LIST){
      cp_read_tm_cut_list(cp, cp->par.warm_start_file_name);
   }else if (!cp->cuts){
      cp->cuts = (cp_cut_data **) calloc (cp->par.block_size,
					  sizeof(cp_cut_data *));
      cp->allocated_cut_num = cp->par.block_size;
   }
}
