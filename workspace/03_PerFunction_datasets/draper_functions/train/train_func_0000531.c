can_handle(int parent, int child)
{
    return (parent == 0 && child == ELM_multistatus) ||
        (parent == ELM_multistatus && child == ELM_response) ||
        (parent == ELM_response &&
         (child == ELM_href || child == ELM_status ||
          child == ELM_propstat || child == ELM_responsedescription)) ||
        (parent == ELM_propstat &&
         (child == ELM_prop || child == ELM_status ||
          child == ELM_responsedescription));
}
