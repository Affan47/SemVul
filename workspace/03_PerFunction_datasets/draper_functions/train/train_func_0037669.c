str_cat_three(string_ty *s1, string_ty *s2, string_ty *s3)
{
    static stracc_t ac;
    ac.clear();
    ac.push_back(s1->str_text, s1->str_length);
    ac.push_back(s2->str_text, s2->str_length);
    ac.push_back(s3->str_text, s3->str_length);
    return ac.mkstr();
}
