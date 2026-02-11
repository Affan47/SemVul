p_inverse_set(FlatZincSpace& s, const ConExpr& ce, AST::Node*) {
      int xoff = ce[2]->getInt();
      int yoff = ce[3]->getInt();
      SetVarArgs x = s.arg2setvarargs(ce[0],xoff);
      SetVarArgs y = s.arg2setvarargs(ce[1],yoff);
      channel(s, x, y);
    }
