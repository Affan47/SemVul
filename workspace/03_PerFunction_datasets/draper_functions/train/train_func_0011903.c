dump()
{
  gold_info("Free list:\n     start      end   length\n");
  for (Iterator p = this->list_.begin(); p != this->list_.end(); ++p)
    gold_info("  %08lx %08lx %08lx", static_cast<long>(p->start_),
	      static_cast<long>(p->end_),
	      static_cast<long>(p->end_ - p->start_));
}
