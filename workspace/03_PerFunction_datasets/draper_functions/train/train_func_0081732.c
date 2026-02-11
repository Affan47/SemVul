test_op(int op, int v1, int v2) {
  switch(op) {
    case TK_EQ: return v1 == v2;
    case TK_LEQ: return v1 <= v2;
    case TK_GEQ: return v1 >= v2;
    case TK_NEQ: return v1 != v2;
    case '<': return v1 < v2;
    case '>': return v1 > v2;
  }
}
