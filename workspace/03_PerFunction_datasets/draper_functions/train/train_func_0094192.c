releasePackedMatrix() const
{
     delete matrix_;
     delete [] lengths_;
     matrix_ = NULL;
     lengths_ = NULL;
}
