yy_1_ReferenceLinkDouble(yycontext *ctx, char *yytext, int yyleng)
{
#define b ctx->val[-1]
#define a ctx->val[-2]
#define yy ctx->yy
#define yypos ctx->pos
#define yythunkpos ctx->thunkpos
  yyprintf((stderr, "do yy_1_ReferenceLinkDouble\n"));
     link match;
                           if (find_reference(&match, b->children)) {
                               yy = mk_link(a->children, match.url, match.title);
                               free(a);
                               free_element_list(b);
                           } else {
                               element *result;
                               result = mk_element(LIST);
                               result->children = cons(mk_str("["), cons(a, cons(mk_str("]"), cons(mk_str(yytext),
                                                   cons(mk_str("["), cons(b, mk_str("]")))))));
                               yy = result;
                           }
                       ;
#undef yythunkpos
#undef yypos
#undef yy
#undef b
#undef a
}
