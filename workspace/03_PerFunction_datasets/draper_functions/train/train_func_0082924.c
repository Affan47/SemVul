operator< ( const subdir_and_target &other ) const
    { return ( subdir_ < other.subdir_ ||
               subdir_ == other.subdir_ &&
               target_ < other.target_ ); }
