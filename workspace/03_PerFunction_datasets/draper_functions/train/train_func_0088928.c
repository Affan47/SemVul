find_closest_any_boundary_iterator() {
        std::list<find_bound_t>::reverse_iterator I;
        for (I = scope.rbegin(); I != scope.rend(); ++I) {
            find_bound_t& T = *I;
            if (T.is_boundary) return T.iter;
        }
        return NULL;
    }
