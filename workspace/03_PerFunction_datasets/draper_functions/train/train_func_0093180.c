clamp(double v) {
  if ((v<min)==(min<=max)) return min;
  else if ((v>max)==(min<=max)) return max;
  else return v;
}
