addCombiningTriple(uint32_t lead, uint32_t trail, uint32_t combined) {
    CombiningTriple *triple;

    if(DO_NOT_STORE(UGENNORM_STORE_COMPOSITION)) {
        return;
    }


    createNorm(lead)->combiningFlags|=1;
    createNorm(trail)->combiningFlags|=2;

    addCombiningCP(lead, 1);
    addCombiningCP(trail, 2);

    triple=(CombiningTriple *)utm_alloc(combiningTriplesMem);
    triple->lead=lead;
    triple->trail=trail;
    triple->combined=combined;
}
