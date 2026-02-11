contains(const vec3& p) const {

    for(int i=0; i < 6; i++) {
        float dist = planes[i].distance(p);

        if(dist < 0) return false;
    }

    return true;
}
