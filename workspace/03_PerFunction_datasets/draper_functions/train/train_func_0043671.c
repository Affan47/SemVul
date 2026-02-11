make_sub_expr(long val, NetExpr*expr)
{
      verinum val_v (val, expr->expr_width());
      val_v.has_sign(true);

      NetEConst*val_c = new NetEConst(val_v);
      val_c->set_line(*expr);

      NetEBAdd*res = new NetEBAdd('-', val_c, expr);
      res->set_line(*expr);

      return res;
}
