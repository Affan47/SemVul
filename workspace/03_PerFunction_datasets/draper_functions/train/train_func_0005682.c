mtdpe_skip_to(TermDocEnum *tde, int target_doc_num)
{
    TermDocEnum *sub_tde;
    PriorityQueue *mtdpe_pq = MTDPE(tde)->pq;

    while (NULL != (sub_tde = (TermDocEnum *)pq_top(mtdpe_pq))
           && (target_doc_num > sub_tde->doc_num(sub_tde))) {
        if (sub_tde->skip_to(sub_tde, target_doc_num)) {
            pq_down(mtdpe_pq);
        }
        else {
            sub_tde = pq_pop(mtdpe_pq);
            sub_tde->close(sub_tde);
        }
    }
    return tde->next(tde);
}
