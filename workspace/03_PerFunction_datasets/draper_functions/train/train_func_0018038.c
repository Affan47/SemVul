main(int argc, char* argv[]) {
    vector<string> encodings(numsymbs,"");


    if (argc == 2 && strncmp(argv[1],"-e",2) == 0) {
        vector<double> freqs(numsymbs,0);
        auto bytes_read = compute_freqs(cin, freqs);
        hufftree = generate_tree(freqs);
        cout << bytes_read - 1 << " ";
        write_htree(hufftree, cout);
        cout << endl;
        generate_encodings(hufftree, encodings);
        cerr << "Entropy: " << compute_entropy(freqs) << "\tCost: " << compute_cost(freqs,encodings) << endl;
    }


    else if (argc == 2 && strncmp(argv[1], "-p",2) == 0) {
        unsigned bytecount;
        cin >> bytecount;
        hufftree = read_htree(cin);
        generate_encodings(hufftree, encodings);
        for (unsigned b = 0; b < encodings.size(); ++b) {


            if (encodings[b] != "") {
                cout << b << " " << encodings[b] << endl;
            }
        }
    }


    else if (argc == 2 && strncmp(argv[1], "-f",2) == 0) {
        vector<double> freqs(numsymbs,0);
        compute_freqs(cin, freqs);
        for (unsigned i = 0; i < freqs.size(); ++i) {
            cout << freqs[i] << endl;
        }
    }


    else if (argc == 3 && strncmp(argv[1], "-c",2) == 0) {
        ifstream tree_file(argv[2]);

        if (!tree_file.is_open()) {
            cerr << "Error, file " << *(argv[2]) << " could not be opened\n"
                    "to define the htree." << endl;
        }
        unsigned bytecount;
        tree_file >> bytecount;
        hufftree = read_htree(tree_file);
        encode(cin, cout);
    }


    else if (argc == 3 && strncmp(argv[1], "-d",2) == 0) {
        ifstream tree_file(argv[2]);
        if (!tree_file.is_open()) {
            cerr << "Error, file " << *(argv[2]) << " could not be opened\n"
                    "to define the htree." << endl;
        }
        unsigned bytecount;
        tree_file >> bytecount;
        hufftree = read_htree(tree_file);
        decode(cin, cout, bytecount);
    }


    else {
        cout << usage_string;
        return 0;
    }
}
