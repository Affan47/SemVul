type1_command(int cmd)
{
    switch (cmd) {

      case Cs::cCallsubr: {
	  if (size() < 1)
	      goto unknown;
	  int subrno = (int)top(0);
	  int renumber_subrno = (subrno >= 0 && subrno < _renumbering->size() ? (*_renumbering)[subrno] : subrno);
	  if (renumber_subrno >= 0) {
	      top(0) = renumber_subrno;
	      goto unknown;
	  }
	  pop();
	  if (Charstring *subr_cs = get_subr(subrno)) {
	      _subr_level++;
	      subr_cs->process(*this);
	      _subr_level--;
	  }
	  return !done();
      }

      case Cs::cEndchar:
	set_done();
	goto end_cs;

      case Cs::cReturn:
	if (_subr_level)
	    return false;
	goto end_cs;

      end_cs:
	_gen.gen_stack(*this, cmd);
	_gen.gen_command(cmd);
	return false;

      default:
      unknown:
	_gen.gen_stack(*this, cmd);
	_gen.gen_command(cmd);
	break;

    }
    return true;
}
