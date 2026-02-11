rossc_skip_to(Scorer *self, int doc_num)
{
    Scorer *req_scorer = ROSSc(self)->req_scorer;
    if (req_scorer->skip_to(req_scorer, doc_num)) {
        self->doc = req_scorer->doc;
        return true;
    }
    return false;
}
