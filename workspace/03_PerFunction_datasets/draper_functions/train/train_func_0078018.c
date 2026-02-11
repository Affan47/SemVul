main(int argc, char **argv) {
    try {

        stringstream *i = new stringstream;
        (*i)<<argv[1]<<" "<<argv[2];
        int cycles, size;
        (*i)>>size>>cycles;
        delete i;

        int alpha[] = {5,2,0,0,5};
        population<iphen_t> p(member<iphen_t>(alpha), size);
        p.print();
        p.evolve(cycles);
        p.print();
        cout<<"Size: "<<p.size()<<endl;
    } catch(exception& e) {
        cout<<e.what()<<endl;
    }
    return 0;
}
