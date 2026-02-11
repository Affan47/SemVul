set_dirc_info( Hmdf_table *hmdf_head )
{
    Hmdf_table *hmdf;
    Dirc_info *tail, *head;

    head = NULL;

    for( hmdf = hmdf_head; hmdf; hmdf = hmdf->next ){
        if( hmdf->pc_num * hmdf->pe_num > 0 ){

            if( head == NULL ){
                head = malloc_dirc_info();
                head->pc_num = hmdf->pc_num;
                head->pe_num = hmdf->pe_num;
                head->pcpe_num = hmdf->pc_num * hmdf->pe_num;
                head->scheduling = hmdf->scheduling;
                head->tron = hmdf->tron;
                tail = head;

            }else{
                tail->next = malloc_dirc_info();
                tail = tail->next;
                tail->pc_num = hmdf->pc_num;
                tail->pe_num = hmdf->pe_num;
                tail->pcpe_num = hmdf->pc_num * hmdf->pe_num;
                tail->scheduling = hmdf->scheduling;
                tail->tron = hmdf->tron;
            }
        }
    }

    return( head );
}
