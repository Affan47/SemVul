report_sortby(choice sortby, logical sub) {
  if (sub)
    printf("    Sorting sub-items ");
  else
    printf("    Sorting ");
  if (sortby == ALPHABETICAL)
    printf("alphabetically\n");
  else if (sortby == RANDOM)
    printf("randomly\n");
  else if (sortby == REQUESTS)
    printf("by number of requests\n");
  else if (sortby == REQUESTS7)
    printf("by number of requests in the last 7 days\n");
  else if (sortby == PAGES)
    printf("by number of requests for pages\n");
  else if (sortby == PAGES7)
    printf("by number of requests for pages in the last 7 days\n");
  else if (sortby == DATESORT)
    printf("by date of last request\n");
  else if (sortby == FIRSTDATE)
    printf("by date of first request\n");
  else if (sortby == BYTES)
    printf("by number of bytes\n");
  else
    printf("by number of bytes in the last 7 days\n");
}
