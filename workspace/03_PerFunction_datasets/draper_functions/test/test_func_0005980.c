add_XSTR(UI_XSTR *xstr)
{
	int idx;
	int found = -1;
	UI_XSTR *ui_x;


	for(idx=0; idx<MAX_UI_XSTRS; idx++){
		if(xstrs[idx] == NULL){
			found = idx;
			break;
		}
	}


	if(found < 0){
		Int3();
		return;
	}


	xstrs[idx] = (UI_XSTR*)vm_malloc(sizeof(UI_XSTR));
	if(xstrs[idx] == NULL){
		return;
	}
	ui_x = xstrs[idx];


	ui_x->xstr = vm_strdup(xstr->xstr);
	if(ui_x->xstr == NULL){
		vm_free(ui_x);
		xstrs[idx] = NULL;
		return;
	}
	ui_x->xstr_id = xstr->xstr_id;
	ui_x->x = xstr->x;
	ui_x->y = xstr->y;
	ui_x->assoc = xstr->assoc;
	ui_x->font_id = xstr->font_id;
	ui_x->clr = xstr->clr;
	Assert((ui_x->clr >= 0) && (ui_x->clr < UI_NUM_XSTR_COLORS));
	if((ui_x->clr < 0) || (ui_x->clr >= UI_NUM_XSTR_COLORS)){
		ui_x->clr = 0;
	}
}
