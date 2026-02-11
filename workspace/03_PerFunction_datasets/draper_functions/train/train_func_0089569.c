handle_write(const boost::system::error_code& e)
		{
			if (!e)
			{

				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			if (e != boost::asio::error::operation_aborted)
			{
				connection_manager_.stop(shared_from_this());
			}
		}
