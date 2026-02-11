round(double r)
  {
    return static_cast<int>( (r > 0.0) ? r + 0.5 : r - 0.5 );
  }
