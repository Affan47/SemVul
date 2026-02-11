set_loop_info_for_du_element(Loop_info_list_alist *infoList,
			     Element              *headElem)
{
    Element  *currElem = headElem;
    Element  *currDimElem = NULL;
    Sub_data *currData = NULL;

    while(currElem != NULL){
	currDimElem = currElem;
	while(currDimElem != NULL){
	    currData = currDimElem->sub_script;
	    while(currData != NULL){
		set_loop_var_entry(infoList, currData);
		currData = currData->next;
	    }
	    currDimElem = currDimElem->next_dim;
	}
	currElem = currElem->next;
    }
}
