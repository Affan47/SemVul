lcp_info(tMSS& file_map)
{
    typedef int_vector<>::size_type size_type;
    int_vector_file_buffer<> lcp_buf(file_map["lcp"].c_str());
    size_type n = lcp_buf.int_vector_size;

    size_type max_lcp = 0;
    size_type sum_lcp = 0;
    for (size_type i=0, r_sum=0, r=0; i < n;) {
        for (; i < r_sum+r; ++i) {
            if (lcp_buf[i-r_sum] > max_lcp)
                max_lcp = lcp_buf[i-r_sum];
            sum_lcp += lcp_buf[i-r_sum];
        }
        r_sum += r; r = lcp_buf.load_next_block();
    }
    std::cout<<"# max lcp = " << max_lcp << std::endl;
    std::cout<<"# sum lcp = " << sum_lcp << std::endl;
    std::cout<<"# avg lcp = " << sum_lcp/(double)n << std::endl;
}
