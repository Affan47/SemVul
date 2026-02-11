operator<(const Model& rhs) const


{

    const Fiction& rhsCopy = static_cast<const Fiction &>(rhs);

    string lhsAuthor = Util::toLowerCase(this->author);
    string rhsAuthor = Util::toLowerCase(rhsCopy.author);
    if (lhsAuthor < rhsAuthor) {
        return true;
    } else if (lhsAuthor == rhsAuthor) {

        if (Util::toLowerCase(this->title) < Util::toLowerCase(rhsCopy.title)) {
            return true;
        }
    }
    return false;
}
