addr_list_get_const(const addr_list_header* slh, const ioa_addr* key) {

  if(!slh || !key) return NULL;

  size_t i;

  for(i=0;i<ADDR_ARRAY_SIZE;++i) {
	  const addr_elem *elem=&(slh->main_list[i]);
	  if(elem->value) {
		  if(addr_eq(&(elem->key),key)) {
			  return elem;
		  }
	  }
  }

  if(slh->extra_list) {
    	  for(i=0;i<slh->extra_sz;++i) {
    		  const addr_elem *elem=&(slh->extra_list[i]);
    		  if(elem->value) {
    			  if(addr_eq(&(elem->key),key)) {
    				  return elem;
    			  }
    		  }
    	  }
  }

  return NULL;
}
