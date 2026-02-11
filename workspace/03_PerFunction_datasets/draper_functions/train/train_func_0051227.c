main() {
    const unsigned int ones[20] = {
        0,

        3,
        3,
        5,
        4,
        4,
        3,
        5,
        5,
        4,
        3,
        6,
        6,
        8,
        8,
        7,
        7,
        9,
        8,
        8
    };

    const unsigned int decades[10] = {
        0,
        0,
        6,
        6,
        5,
        5,
        5,
        7,
        6,
        6,
    };

    unsigned int count = 0;
    for (unsigned int i = 1; i < 1000; ++i) {
        if (99 < i) {
            count += ones[i / 100] + 7;
        }

        if (99 < i && 0 < i % 100) {
            count += 3;
        }

        if (19 < i % 100) {
            count += decades[i / 10 % 10] + ones[i % 10];
        } else {
            count += ones[i % 100];
        }
    };

    count += 11;

    cout << "The total number of letters needed to spell out all numbers"
         << "\nfrom 1 to 1000 is: " << count << endl;
}
