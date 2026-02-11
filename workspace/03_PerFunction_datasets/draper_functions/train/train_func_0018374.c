equals(const Requirement& r, float epsilon) const {
    if (!Math::equal(natural_, r.natural_, epsilon)) {
        return false;
    } else if (!Math::equal(stretch_, r.stretch_, epsilon)) {
        return false;
    } else if (!Math::equal(shrink_, r.shrink_, epsilon)) {
        return false;
    } else if (!Math::equal(alignment_, r.alignment_, epsilon)) {
        return false;
    } else {
        return true;
    }
}
