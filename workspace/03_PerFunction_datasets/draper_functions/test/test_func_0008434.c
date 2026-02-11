Ref_Stipple(const Stipple* p) {
    if (p != no_stipple) {
        Resource::ref(p);
    }
}
