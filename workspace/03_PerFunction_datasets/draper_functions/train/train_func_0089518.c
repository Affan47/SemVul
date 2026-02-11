expr_2n(Interp &interp, const RefPtr<Expr> &arg, const RefPtr<Obj> &)
    {
      Val tmp_self=interp.top_scope()->self();

      if(tmp_self.obj()->is_method("m")) {
        const Method &method=tmp_self.obj()->method("m");
        RefPtr<Expr> tmp_tree=method.expr();

        if(tmp_tree.get()!=0) {
          istringstream iss(tmp_tree->str());
          int n;

          iss >> n;
          if(iss.eof()) {
            return interp.num_val(n);
          }
        }
      }
      return interp.nil_val();
    }
