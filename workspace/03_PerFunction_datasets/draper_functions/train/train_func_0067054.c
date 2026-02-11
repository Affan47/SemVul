OpSaveStatusAll()
{
   dac_savestatusall_ot out ;
   process_t *p_p ;

   for (p_p = process_list ; p_p != NULL ; p_p = p_p->next)
	  p_p->retflag = YES ;
}
