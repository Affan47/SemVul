coord_between(fixed start, fixed mid, fixed end)
{
    return (start <= end ? start <= mid && mid <= end :
            start >= mid && mid >= end);
}
