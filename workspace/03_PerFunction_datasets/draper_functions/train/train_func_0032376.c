H5S_hyper_cmp_spans (H5S_hyper_span_info_t *span_info1, H5S_hyper_span_info_t *span_info2)
{
    H5S_hyper_span_t *span1;
    H5S_hyper_span_t *span2;
    htri_t nest=FAIL;
    htri_t ret_value=FAIL;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    if(span_info1==span_info2)
        ret_value=TRUE;
    else {

        if(span_info1==NULL && span_info2==NULL)
            ret_value=TRUE;
        else {

            if(span_info1==NULL || span_info2==NULL)
                ret_value=FALSE;
            else {

                span1=span_info1->head;
                span2=span_info2->head;


                HDassert(span1);
                HDassert(span2);


                while (1) {

                    if(span1==NULL && span2==NULL) {
                        ret_value=TRUE;
                        break;
                    }
                    else {

                        if(span1==NULL || span2==NULL) {
                            ret_value=FALSE;
                            break;
                        }
                        else {

                            if(span1->low!=span2->low || span1->high!=span2->high) {
                                ret_value=FALSE;
                                break;
                            }
                            else {
                                if(span1->down!=NULL || span2!=NULL) {
                                    if((nest=H5S_hyper_cmp_spans(span1->down,span2->down))==FAIL) {
                                        ret_value=FAIL;
                                        break;
                                    }
                                    else {
                                        if(nest==FALSE) {
                                            ret_value=FALSE;
                                            break;
                                        }
                                        else {

                                        }
                                    }
                                }
                                else {

                                }
                            }
                        }
                    }


                    span1=span1->next;
                    span2=span2->next;
                }
            }
        }
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
