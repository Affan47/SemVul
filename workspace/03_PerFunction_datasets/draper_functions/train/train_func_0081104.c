del_entry(struct sockaddr_atmpvc *from,struct sockaddr_atmpvc *to)
{
    LINK *l_from,*l_to;
    TABLE **entry,*this;

    l_from = find_link(from->sap_addr.itf);
    l_to = find_link(to->sap_addr.itf);
    if (!l_from || !l_to) return -ENODEV;
    for (entry = &l_from->table; *entry; entry = &(*entry)->next)
	if ((*entry)->out == l_to && (*entry)->in_vpi == from->sap_addr.vpi &&
	  (*entry)->in_vci == from->sap_addr.vci &&
	  ((*entry)->in_vci == ATM_VCI_UNSPEC ||
	  (*entry)->out_vci == to->sap_addr.vci))
	    break;
    if (!*entry) return -EHOSTUNREACH;
    this = *entry;
    *entry = this->next;
    if (this->in_vci == ATM_VCI_UNSPEC)
	diag(COMPONENT,DIAG_INFO,"deleted VP %d.%d -> %d.%d",l_from->id,
	  this->in_vpi,l_to->id,this->out_vpi);
    else diag(COMPONENT,DIAG_INFO,"deleted VC %d.%d.%d -> %d.%d.%d",l_from->id,
	  this->in_vpi,this->in_vci,l_to->id,this->out_vpi,this->out_vci);
    free(this);
    return 0;
}
