free_pat(PAT_S **pat)
{
    if(pat && *pat){
	free_pat(&(*pat)->next);
	free_patgrp(&(*pat)->patgrp);
	free_action(&(*pat)->action);
	if((*pat)->raw)
	  fs_give((void **)&(*pat)->raw);

	fs_give((void **)pat);
    }
}
