call(Interp &interp, const Val &rcvr, const RefPtr<Expr> &arg, const Ptr<Tail> &tail) const
  {
    PushScopeGuard ps_guard(interp, new Scope(rcvr.obj()->scope()));
    Val tmp_r;


    if(!m_has_first_self) {
      interp.top_scope()->set_self(rcvr);
    } else {
      interp.top_scope()->set_self(interp.top_scope()->first_self());
      interp.top_scope()->unset_first_self();
    }
    if(is_expr()) {
      interp.top_scope()->def_var(m_arg_name, Var(arg, interp.prev_scope()));
#if 0
      tmp_r=m_expr->eval(interp);
#else
      if(tail.get()==0) {
        Tail tmp_tail;

        while((tmp_r=m_expr->eval(interp, &tmp_tail)).obj().get()==0) {
          interp.pop_scope();
          interp.push_scope(tmp_tail.scope);
          tmp_tail.expr=Ptr<Expr>();
        }
      } else {
        tmp_r=m_expr->eval(interp, tail);
      }
#endif
    } else {
      tmp_r=(*m_fptr)(interp, arg, m_data);
    }

    return tmp_r;
  }
