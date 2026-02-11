main() {
    int limit = 2000000;
    int primes[2000000];
    euler_sieve(limit, primes);
    int i = 0;
    double sum = 0;
    for (i = 2; i < 2000000; i++) {
        if (primes[i] == 1) {
            sum += i;
        }
    }
    printf("The sum of all primes below 2000000 is %f\n", sum);
}
