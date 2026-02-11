generate_sent_block(ast_sentblock* sb, bool need_brace) {
    std::list<ast_sent*> &sents = sb->get_sents();

    std::list<ast_sent*>::iterator i;
    if (need_brace) _Body.pushln("{");
    for (i = sents.begin(); i != sents.end(); i++) {
        ast_sent* s = *i;
        generate_sent(s);
    }
    if (need_brace) _Body.pushln("}");
}
