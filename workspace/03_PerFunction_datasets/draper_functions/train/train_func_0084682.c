dump(ostream&out, unsigned ind) const
{
      out << setw(ind) << "";
      switch (type()) {
	  case PGBuiltin::BUFIF0:
	    out << "bufif0 ";
	    break;
	  case PGBuiltin::BUFIF1:
	    out << "bufif1 ";
	    break;
	  case PGBuiltin::NOTIF0:
	    out << "bufif0 ";
	    break;
	  case PGBuiltin::NOTIF1:
	    out << "bufif1 ";
	    break;
	  case PGBuiltin::NAND:
	    out << "nand ";
	    break;
	  case PGBuiltin::NMOS:
	    out << "nmos ";
	    break;
	  case PGBuiltin::RNMOS:
	    out << "rnmos ";
	    break;
	  case PGBuiltin::RPMOS:
	    out << "rpmos ";
	    break;
	  case PGBuiltin::PMOS:
	    out << "pmos ";
	    break;
	  case PGBuiltin::RCMOS:
	    out << "rcmos ";
	    break;
	  case PGBuiltin::CMOS:
	    out << "cmos ";
	    break;
	  default:
	    out << "builtin gate ";
      }

      out << "(" << strength0() << "0 " << strength1() << "1) ";
      dump_delays(out);
      out << " " << get_name();

      if (msb_) {
	    out << " [" << *msb_ << ":" << *lsb_ << "]";
      }

      out << "(";
      dump_pins(out);
      out << ");" << endl;
}
