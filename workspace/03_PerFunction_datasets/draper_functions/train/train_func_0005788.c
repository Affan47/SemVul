act124()
{
		NLA = 56;

    pushint(']');
    if ( GenCC ) {
      if (NewAST) zzreplstr("(newAST(");
      else zzreplstr("(new AST("); }
    else zzreplstr("zzmk_ast(zzastnew(),");
    zzmore();
    chkGTFlag();
	}
