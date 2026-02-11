has_dup(const vec_basic &arg)
{
    map_basic_basic d;
    auto it = d.end();
    for (auto &p: arg) {
        it = d.find(p);
        if (it == d.end()) {
            insert(d, p, one);
        } else {
            return true;
        }
    }
    return false;
}
