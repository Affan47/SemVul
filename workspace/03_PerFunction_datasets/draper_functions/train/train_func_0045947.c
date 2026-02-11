addItinerary(const Itinerary &itinerary) {
#ifdef __DEBUG_ITINERARY
  printf("ADD ITINERARY: \n");
    passenger* test = people->find(itinerary.lastName, itinerary.firstName);
    if (!test)
      printf("%s %s is not in hash.  Adding...\n", itinerary.firstName, itinerary.lastName);
#endif
    passenger* p = people->insert(itinerary.lastName, itinerary.firstName);
#ifdef __DEBUG_ITINERARY
    if (!test) {
      test = people->find(itinerary.lastName, itinerary.firstName);
      if (test == p )
        printf("Retrieved %s %s successfully at %p.\n", p->name.firstName, p->name.lastName, test);
      else
        printf(
          "ERROR: Could not retrieve %s %s.  Got %p, expected %p.\n",
          itinerary.firstName,
          itinerary.lastName,
          test,
          p
        );
    }
#endif
    for (int i=0; i< itinerary.flightCount; ++i) {

#ifdef __DEBUG_ITINERARY
      printf(
        "  Adding flight %d/%d to pFlight in pos #%d...\n",
        itinerary.dates[i],
        itinerary.flightNums[i],
        p->flightCount
      );
#endif

      flight* f = flights[itinerary.dates[i]][itinerary.flightNums[i]];
      if (!f) {
#ifdef __DEBUG_ITINERARY
        printf("    flight doesn't exist.  Creating...\n");
#endif
        f = new flight(itinerary.dates[i], itinerary.flightNums[i]);
        flights[itinerary.dates[i]][itinerary.flightNums[i]] = f;
      }
#ifdef __DEBUG_ITINERARY
      printf(
        "  Found flight at %d/%d, which claims to be %d/%d and has %d passengers\n",
        itinerary.dates[i],
        itinerary.flightNums[i],
        f->date,
        f->flightnum,
        f->passengerCount
      );
#endif
      f->passengers[f->passengerCount++] = p;
#ifdef __DEBUG_ITINERARY
      printf("    Passenger inserted into flight. PassengerCount now %d\n", f->passengerCount);
#endif
      p->pFlights[p->flightCount++] = f;
#ifdef __DEBUG_ITINERARY
      printf("    Flight inserted into passenger. FlightCount now %d\n", p->flightCount);
#endif
    }
#ifdef __DEBUG_ITINERARY
  printf("\n");
#endif
}
