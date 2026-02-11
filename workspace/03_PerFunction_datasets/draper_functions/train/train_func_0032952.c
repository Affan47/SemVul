oc_quant_params_clear(th_quant_info *_qinfo){
  int i;
  for(i=6;i-->0;){
    int qti;
    int pli;
    qti=i/3;
    pli=i%3;

    if(i>0){
      int qtj;
      int plj;
      qtj=(i-1)/3;
      plj=(i-1)%3;
      if(_qinfo->qi_ranges[qti][pli].sizes==
       _qinfo->qi_ranges[qtj][plj].sizes){
        _qinfo->qi_ranges[qti][pli].sizes=NULL;
      }
      if(_qinfo->qi_ranges[qti][pli].base_matrices==
       _qinfo->qi_ranges[qtj][plj].base_matrices){
        _qinfo->qi_ranges[qti][pli].base_matrices=NULL;
      }
    }
    if(qti>0){
      if(_qinfo->qi_ranges[1][pli].sizes==
       _qinfo->qi_ranges[0][pli].sizes){
        _qinfo->qi_ranges[1][pli].sizes=NULL;
      }
      if(_qinfo->qi_ranges[1][pli].base_matrices==
       _qinfo->qi_ranges[0][pli].base_matrices){
        _qinfo->qi_ranges[1][pli].base_matrices=NULL;
      }
    }

    _ogg_free((void *)_qinfo->qi_ranges[qti][pli].sizes);
    _ogg_free((void *)_qinfo->qi_ranges[qti][pli].base_matrices);
  }
}
