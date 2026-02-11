rdiv(const Number &other) const
{
    if (is_a<Integer>(other)) {
        if (this->i == 0) {
            throw std::runtime_error("Rational: Division by zero.");
        }
        mpq_class q((static_cast<const Integer&>(other)).i, this->i);


        q.canonicalize();

        return Rational::from_mpq(q);
    } else {
        throw std::runtime_error("Not implemented.");
    }
}
