parse_term(Parser *p){
    AVEvalExpr * e = parse_factor(p);
    while(p->s[0]=='*' || p->s[0]=='/'){
        int c= *p->s++;
        e= new_eval_expr(c == '*' ? e_mul : e_div, 1, e, parse_factor(p));
    }
    return e;
}
