ReadFloatValue()
{


  int c;
  while (isspace(c = this->Getc()))
    {
    if (c == '\n')
      {
      ++this->Superclass::LineNumber;
#if VTK_FOAMFILE_RECOGNIZE_LINEHEAD
      this->Superclass::WasNewline = true;
#endif
      }
    }
  if (c == 47)
    {
    this->PutBack(c);
    c = this->NextTokenHead();
    }


  int nonNegative = c - 45;
  if (nonNegative == 0 || c == 43)
    {
    c = this->Getc();
    if (c == '\n')
      {
      ++this->Superclass::LineNumber;
#if VTK_FOAMFILE_RECOGNIZE_LINEHEAD
      this->Superclass::WasNewline = true;
#endif
      }
    }

  if (!isdigit(c) && c != 46)
    {
    this->ThrowUnexpectedNondigitCharExecption(c);
    }


  double num = c - 48;
  while (isdigit(c = this->Getc()))
    {
    num = num * 10.0 + (c - 48);
    }


  if (c == 46)
    {
    double divisor = 1.0;

    while (isdigit(c = this->Getc()))
      {
      num = num * 10.0 + (c - 48);
      divisor *= 10.0;
      }
    num /= divisor;
    }


  if (c == 69 || c == 101)
    {
    int esign = 1;
    int eval = 0;
    double scale = 1.0;

    c = this->Getc();
    if (c == 45)
      {
      esign = -1;
      c = this->Getc();
      }
    else if (c == 43)
      {
      c = this->Getc();
      }

    while (isdigit(c))
      {
      eval = eval * 10 + (c - 48);
      c = this->Getc();
      }


    while (eval >= 64)
      {
      scale *= 1.0e+64;
      eval -= 64;
      }
    while (eval >= 16)
      {
      scale *= 1.0e+16;
      eval -= 16;
      }
    while (eval >= 4)
      {
      scale *= 1.0e+4;
      eval -= 4;
      }
    while (eval >= 1)
      {
      scale *= 1.0e+1;
      eval -= 1;
      }

    if (esign < 0)
      {
      num /= scale;
      }
    else
      {
      num *= scale;
      }
    }

  if (c == EOF)
    {
    this->ThrowUnexpectedEOFException();
    }
  this->PutBack(c);

  return static_cast<float>(nonNegative ? num : -num);
}
