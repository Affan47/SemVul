operator=( const Ngram& other )
{
    if (&other != this) {
	for (int i = 0; i < N; i++) {
	    ngrams[i] = other.ngrams[i];
	}
    }

    return *this;
}
