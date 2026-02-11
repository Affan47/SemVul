divint(const Integer &other) const {
    if (other.i == 0)
        throw std::runtime_error("Rational: Division by zero.");
    mpq_class q(this->i, other.i);


    q.canonicalize();

    return Rational::from_mpq(q);
}
