operator<<(Expression& E)
{
  if (__ostream != 0) {
    (*__ostream) << E;
  } else {
    ASSERT(__ofstreamVariable->expression()->ofstream() != 0);
    (*__ofstreamVariable->expression()->ofstream()) << E << std::flush;
  }
}
