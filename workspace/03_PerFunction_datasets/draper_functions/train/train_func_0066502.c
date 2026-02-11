check_int(struct csa *csa, double num)
{
      if (!csa->nonint && num != floor(num))
      {  warning(csa, "non-integer data detected");
         csa->nonint = 1;
      }
      return;
}
