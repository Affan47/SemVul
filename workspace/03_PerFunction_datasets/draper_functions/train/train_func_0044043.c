print(FILE* f) const
{
  fprintf(f, "  %s", this->name_.c_str());

  unsigned int attrs = this->attributes_;
  if (attrs != 0)
    {
      fprintf(f, " (");
      do
	{
	  switch (attrs & - attrs)
	    {
	    case MEM_EXECUTABLE:  fputc('x', f); break;
	    case MEM_WRITEABLE:   fputc('w', f); break;
	    case MEM_READABLE:    fputc('r', f); break;
	    case MEM_ALLOCATABLE: fputc('a', f); break;
	    case MEM_INITIALIZED: fputc('i', f); break;
	    default:
	      gold_unreachable();
	    }
	  attrs &= ~ (attrs & - attrs);
	}
      while (attrs != 0);
      fputc(')', f);
    }

  fprintf(f, " : origin = ");
  this->start_->print(f);
  fprintf(f, ", length = ");
  this->length_->print(f);
  fprintf(f, "\n");
}
