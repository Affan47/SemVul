add(double val, const char *str, unsigned col) {

  if (numb >= sizenumb) {
    sizenumb += FL_CHART_MAX;
    entries = (FL_CHART_ENTRY *)realloc(entries, sizeof(FL_CHART_ENTRY) * (sizenumb + 1));
  }

  if (numb >= maxnumb && maxnumb > 0) {
    memmove(entries, entries + 1, sizeof(FL_CHART_ENTRY) * (numb - 1));
    numb --;
  }
  entries[numb].val = float(val);
  entries[numb].col = col;
    if (str) {
	strlcpy(entries[numb].str,str,FL_CHART_LABEL_MAX + 1);
    } else {
	entries[numb].str[0] = 0;
    }
  numb++;
  redraw();
}
